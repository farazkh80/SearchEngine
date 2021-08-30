from NewsSummaryDataset import NewsSummaryDataset
import pandas as pd
from torch.utils.data import DataLoader
import pytorch_lightning as pl
from transformers import (
    T5TokenizerFast as T5Tokenizer
)

# News Summary Dataset Module containing the main
# train, test and validation dataloaders to be used
# in model fine-tuning
class NewsSummaryDatasetModule(pl.LightningDataModule):

    def __init__(
        self,
        train_df: pd.DataFrame,
        test_df: pd.DataFrame,
        tokenizer: T5Tokenizer,
        batch_size: int = 8,
        test_max_token_len: int = 512,
        summary_max_token_len: int = 128
    ):
        super().__init__()

        self.train_df = train_df
        self.test_df = test_df

        self.batch_size = batch_size
        self.tokenizer = tokenizer
        self.test_max_token_len = test_max_token_len # used for News Summary Dataset config
        self.summary_max_token_len = summary_max_token_len # used for News Summary Dataset config

    def setup(self, stage=None):
        # create train dataset
        self.train_dataset = NewsSummaryDataset(
            self.train_df,
            self.tokenizer,
            self.test_max_token_len,
            self.summary_max_token_len
        )

        # create test dataset
        self.test_dataset = NewsSummaryDataset(
            self.test_df,
            self.tokenizer,
            self.test_max_token_len,
            self.summary_max_token_len
        )

    def train_dataloader(self):
        return DataLoader(
            self.train_dataset,
            batch_size = self.batch_size,
            shuffle=True,
            num_workers=2
        )

    def val_dataloader(self):
        return DataLoader(
            self.test_dataset,
            batch_size = self.batch_size,
            shuffle=False,
            num_workers=2
        )

    def test_dataloader(self):
        return DataLoader(
            self.test_dataset,
            batch_size = self.batch_size,
            shuffle=False,
            num_workers=2
        )