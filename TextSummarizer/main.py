from os import cpu_count
from pickle import NONE
from types import CodeType
from streamlit.proto.Markdown_pb2 import Markdown
from streamlit.state.session_state import SessionState
import yfinance as yf
from yfinance import ticker
import streamlit as st
import pandas as pd
from FineTuner import FineTuner

def display_header():
    header_container = st.empty()
    header_container.markdown("""
    # Text Summarization Demo with T5
    A fine-tuned T5 model for text summarization
    """)

def display_summaries(text, summaries, container):
    st.set_page_config(layout="wide")
    container.empty()

    total_cols = 1 + len(summaries)
    cols = container.columns(total_cols)

    cols[0].text_area('ORIGINAL TEXT {} words'.format(len(text.split())), value=text, height=300)
    i= 1
    for key,val in summaries.items():
        cols[i].text_area(label='{} Summary {} words'.format(key, len(val.split())), value=val, height=300)
        i+=1
    

def text_summary_component():
    models = []
    if st.session_state.model_choice_t5_base: models.append(('t5-base', 't5-base-full-seeded.ckpt'))
    if st.session_state.model_choice_t5_small: models.append(('t5-small','t5-small-full-seeded.ckpt'))

    display_header()
    summary_container = st.container()
    text = st.session_state.text
    if text:
        # display original text
        summary_container.text_area('Entered Text:', value=text, height=300)

        summaries= {}
        for (model_name,model_path) in models:
            tunner = FineTuner(
                model_name=model_name,
                pre_tuned=True,
                saved_checkpoint_file_name=model_path
            )
            with summary_container.info('Fine-Tunning {}'.format(model_name.title())):
                tunner.fit_and_tune() # fine tunning the model

            with summary_container.success('Summarizing {}'.format(model_name.title())):
                summary = tunner.summarize(text) # summarizing with model 

            summaries[model_name]=summary

        display_summaries(
            text=text,
            summaries=summaries,
            container=summary_container
        )

    else:
        summary_container.error("INVALID INPUT, TRY AGAIN")

def text_search_component():
    return


left_column_sb, right_column_sb = st.sidebar.columns(2)
left_column, right_column = st.columns(2)

if left_column_sb.button(
    label='Summarizing',
    key='summarization-main',
    help='Click for Summarization Functionality'
    ):
    display_header()
    summary_container = st.container()
    text = st.text_area("Original Text", key="text", height=300)
    st.button(
        label='Summarize',
        key='summarize',
        on_click=text_summary_component,
    )

elif right_column_sb.button(
    label='Searching',
    key='searching-main',
    help='Click for Searching'
    ):
    display_header()
    st.text_input("Search Keyword", key="keyword")
    st.button(label='Search', key='search', on_click=text_search_component)

else:
    md_container = st.empty()
    md_container.markdown("""
    # Text Summarization Demo with T5
    A fine-tuned T5 model for text summarization

    ![t5-pic] (https://miro.medium.com/max/1400/1*YHQBMsSowhn4Swl-ctvhDw.png)
    """
    )
    

# models choice check boxes
st.sidebar.write("""
---
Summarization Models
""")

st.sidebar.checkbox(
    label='t5-base',
    value=True,
    key='model_choice_t5_base',
    help='222M Parameters'
)
st.sidebar.checkbox(
    label='t5-small',
    value=False,
    key='model_choice_t5_small',
    help='66M Parameters'
)
st.sidebar.checkbox(
    label='t5-large',
    value=False,
    key='model_choice_t5_large'
)