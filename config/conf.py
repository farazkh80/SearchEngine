from confetti import Config
import os

__all__ = ["config"]

config = Config({
    'os-system': 'win', # change to match running os
    'search_data_path': os.path.join('data','search-data','bigDataset.txt'),
    'search_engine_binary_path': {
        'win': os.path.join('Search-Engine','Search-Engine.exe'),
        'unix': os.path.join('Search-Engine','/searchengine')
    },
    'model_ckpt_path': {
        't5-base': 't5-base-full-seeded.ckpt',
        't5-small': 't5-small-full-seeded.ckpt'
    }
})