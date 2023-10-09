import streamlit as st
import pandas as pd
import numpy as np

add_sidebar = st.sidebar.selectbox('Таблицы', ('ctm', 'railcars', 'railcar_bodies'))

# Initialize connection.
conn = st.experimental_connection("postgresql", type="sql")

# Perform query.
df = conn.query('SELECT * FROM main_schema.ctm;', ttl="10m")

# Print results.
st.dataframe(df)
