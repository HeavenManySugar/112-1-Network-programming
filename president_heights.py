import pandas as pd

df = pd.read_csv('president_heights.csv')

print(df.describe())
print(df.nlargest(5, 'height(cm)'))
print(df[df['height(cm)'] > 180].nsmallest(5, 'height(cm)'))
