import pandas as pd
from pytorch_lightning import Trainer
import torch
from pytorch_lightning.callbacks import ModelCheckpoint
from pytorch_lightning.loggers import TensorBoardLogger
from sklearn.model_selection import train_test_split
from transformers import (
    T5TokenizerFast as T5Tokenizer
)

from NewsSummaryModel import NewsSummaryModel
from NewsSummaryDatasetModule import NewsSummaryDatasetModule

class FineTuner(object):
    def __init__(
        self,
        model_name: str,
        pre_tuned: bool = False,
        saved_checkpoint_file_name: str = None,
        ):
        super().__init__()

        self.pre_tuned = pre_tuned
        self.saved_checkpoint_file_name = saved_checkpoint_file_name
        self.model_name = model_name
        self.tokenizer = T5Tokenizer.from_pretrained(self.model_name)

    def fit_and_tune(
        self,
        dataset_file_relative_path: str = None,
        new_checkpoint_file_name: str =  None,
        gpu_num: int = 0,
        tpu_num: int = 0,
        epochs: int = 3,
        batch_size: int = 8,
        test_size: float = 0.1,
        logger_dir_name: str = 'torch-runs',
        logger_file_name: str = 'news_summary',
        ):
        if self.pre_tuned:
          self.trainer_model = NewsSummaryModel.load_from_checkpoint(model_name=self.model_name,checkpoint_path=self.saved_checkpoint_file_name)

        else:
          # preprocess data
          df = pd.read_csv(dataset_file_relative_path, encoding='latin-1')
          df = df[["text", "ctext"]]
          df.columns = ["summary", "text"]
          self.df = df.dropna()

          # Train test split
          self.train_df, self.test_df = train_test_split(self.df, test_size=test_size)

          # other definitions
          self.epochs=epochs
          self.batch_size=batch_size
          self.gpu_num = gpu_num
          self.tpu_num = tpu_num

          self.data_module = NewsSummaryDatasetModule(self.train_df, self.test_df, self.tokenizer, batch_size=self.batch_size)
          self.model = NewsSummaryModel(self.model_name)

          self.checkpoint_callback = ModelCheckpoint(
              dirpath="checkpoints",
              filename="best-checkpoint",
              save_top_k=1,
              verbose=True,
              monitor="val_loss",
              mode="min"
          )

          self.logger = TensorBoardLogger(logger_dir_name, name=logger_file_name)

          if gpu_num > 0 and torch.cuda.is_available():
              self.trainer = Trainer(
                  logger=self.logger,
                  callbacks=self.checkpoint_callback,
                  max_epochs=self.epochs,
                  gpus=1,
                  progress_bar_refresh_rate=30
              )
          else:
              self.trainer = Trainer(
                  logger=self.logger,
                  callbacks=self.checkpoint_callback,
                  max_epochs=self.epochs,
                  progress_bar_refresh_rate=30
              )

          self.trainer.fit(self.model, self.data_module)
          
          if new_checkpoint_file_name:
            self.trainer.save_checkpoint(new_checkpoint_file_name)
            self.trainer_model = NewsSummaryModel.load_from_checkpoint(model_name=self.model_name,checkpoint_path=new_checkpoint_file_name)
          
          else:
            self.trainer_model = NewsSummaryModel.load_from_checkpoint(
                self.trainer.callbacks[1].best_model_path
            )
            self.trainer_model.freeze()

          


    def summarize(self, text):
        self.text_encoding = self.tokenizer(
            text,
            max_length=512,
            padding="max_length",
            truncation=True,
            return_attention_mask=True,
            add_special_tokens=True,
            return_tensors='pt'
        )

        self.generated_ids = self.trainer_model.model.generate(
            input_ids=self.text_encoding["input_ids"],
            attention_mask=self.text_encoding["attention_mask"],
            max_length=150,
            num_beams=2,
            repetition_penalty=1.0,
            length_penalty=1.0,
            early_stopping=True
        )

        self.preds = [
            self.tokenizer.decode(gen_id, skip_special_tokens=True, clean_up_tokenization_spaces=True)
            for gen_id in self.generated_ids
        ]

        return "".join(self.preds)
    

def main():
    tunner = FineTuner(
        model_name='t5-small',
        pre_tuned=True,
        saved_checkpoint_file_name='t5-small-latest.ckpt'
    )

    tunner.fit_and_tune()
    
    text = "On Sunday, Liberal candidate Chrystia Freeland posted to Twitter a selectively edited clip of O'Toole speaking about health care. \
    In the video, O'Toole said he would be open to more for-profit health care in Canada to help address some of the current system's failings. \
    While willing to add more private elements to medicare, O'Toole said universal access remains paramount — a quote that was left out of Freeland's edited video montage. Twitter has since flagged the clip as \"manipulated media.\" \
    The Conservative party's lawyers have asked Yves Côté, the commissioner of Canada elections, to investigate whether the \"cynical motive to misinform\" is a violation of the Elections Act. \
    Asked about the fracas over the manipulated video, Trudeau said the clip accurately reflects O'Toole position. \
    \"What's really important here is, in the middle of a pandemic, O'Toole came out unequivocally in support of private health care, for-profit health care. We posted the interview in its entirety and I encourage all Canadians to take a look and see what Erin O'Toole has to say on the future of health care,\" he said.\
    In the 2020 video clip posted by Freeland, O'Toole said that to drive innovation in the sector, Canada \"can't have just one old model that is increasingly becoming inefficient,\" and more \"public/private synergies\" are needed to improve health-care outcomes."
    
    summary = tunner.summarize(text)
    print("\n\nSummary: ", summary)

if __name__=="__main__":
    main()

        