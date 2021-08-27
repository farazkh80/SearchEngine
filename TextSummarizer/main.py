import streamlit as st
from FineTuner import FineTuner
import subprocess
st.set_page_config(page_title='T5 MAGIC', layout="wide")

def display_header():
    header_container = st.empty()
    header_container.markdown("""
    # Text Summarization Demo with T5
    A fine-tuned T5 model for text summarization
    """)

def display_summaries(text, summaries, container):
    container.empty()
    for key,val in summaries.items():
        container.text_area(label='{} Summary {} words'.format(key, len(val.split())), value=val, height=300)

    container.text_area('ORIGINAL TEXT {} words'.format(len(text.split())), value=text, height=300)
    
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

def text_searched_summary_component(**kwargs):
    print(kwargs)
    models = []
    if st.session_state.model_choice_t5_base: models.append(('t5-base', 't5-base-full-seeded.ckpt'))
    if st.session_state.model_choice_t5_small: models.append(('t5-small','t5-small-full-seeded.ckpt'))

    display_header()
    summary_container = st.container()
    text = st.session_state[kwargs['text-id']]
    if text:

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

def text_search_component():
    display_header()
    cmd = 'SearchEngine.exe -d ../data/bigDataset.txt -k 3 -m /search -w {}'.format(st.session_state.keyword)
    print(cmd)

    with st.warning('Searching Through the Database'):
        _, out = subprocess.getstatusoutput(cmd)

    search_res = out.split('[CEL]')

    st.success('Displaying Results')
    for res in search_res[:-1]:
        if res[0] == "\n":
            id = res[2:7].strip()
        else:
            id = res[1:7].strip()

        st.text_area(label=id, value=res, key="matched-doc-{}-text".format(id), height=500)
        st.button(
            label='Summarize',
            key="matched-doc-{}-btn".format(id),
            on_click=text_searched_summary_component,
            kwargs={'text-id' : "matched-doc-{}-text".format(id)}
        )
        st.write("""
        ---
        """)


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