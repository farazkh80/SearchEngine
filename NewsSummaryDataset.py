from torch.utils.data import Dataset
import pandas as pd
from transformers import (
    T5TokenizerFast as T5Tokenizer
)

# News Summary Dataset class to be used fot input and output
# data access and tokenization
class NewsSummaryDataset(Dataset):

    def __init__(
        self,
        data: pd.DataFrame,
        tokenizer: T5Tokenizer,
        text_max_token_len: int = 512,
        summary_max_token_len: int = 128
        ):
        super().__init__()
        self.tokenizer = tokenizer
        self.data = data
        self.text_max_token_len = text_max_token_len
        self.summary_max_token_len = summary_max_token_len

    def __len__(self):
        return len(self.data)
    
    def __getitem__(self, index: int):
        data_row = self.data.iloc[index]

        # tokenize input
        text_encoding = self.tokenizer(
            data_row["text"],
            max_length = self.text_max_token_len,
            padding="max_length",
            truncation=True,
            return_attention_mask=True,
            add_special_tokens=True,
            return_tensors="pt"
        )

        # tokenize output
        summary_encoding = self.tokenizer(
            data_row["summary"],
            max_length = self.summary_max_token_len,
            padding="max_length",
            truncation=True,
            return_attention_mask=True,
            add_special_tokens=True,
            return_tensors="pt"
        )

        labels = summary_encoding['input_ids']
        labels[labels == 0] = -100

        return dict(
            text=data_row["text"],
            summary=data_row["summary"],
            text_input_ids=text_encoding["input_ids"].flatten(),
            text_attention_mask=text_encoding["attention_mask"].flatten(),
            labels= labels.flatten(),
            labels_attention_mask= summary_encoding["attention_mask"].flatten()
        )
