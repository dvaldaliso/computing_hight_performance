import matplotlib.pyplot as plt
import pandas as pd
from scipy import stats

df= pd.read_csv("../MOVIES.csv")

coef = df["popularity"].corr(df["budget"],method="pearson")
print(coef)
stat1, p_value1 = stats.shapiro(df['budget'])
stat2, p_value2 = stats.shapiro(df['popularity'])
print(f'Shapiro-Wilk - budget: Estadístico: {stat1}, p-valor: {p_value1}')
print(f'Shapiro-Wilk - popularity: Estadístico: {stat2}, p-valor: {p_value2}')