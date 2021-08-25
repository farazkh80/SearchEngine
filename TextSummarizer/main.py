import yfinance as yf
from yfinance import ticker
import streamlit as st
import pandas as pd
from FineTuner import FineTuner

st.write("""
# Text Summarization Demo with T5

A fine-tuned T5 model for summarizing news
""")

st.text_area("Original Text", key="text", height=500)

if st.button('Summarize'):
    tunner = FineTuner(
        model_name='t5-small',
        pre_tuned=True,
        saved_checkpoint_file_name='t5-small-latest.ckpt'
    )

    tunner.fit_and_tune()

    summary = tunner.summarize(st.session_state.text)
    st.write("LOADING...\n\n")
    st.write(summary)