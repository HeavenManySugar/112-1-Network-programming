import pandas as pd

# Read an Excel file
df = pd.read_excel('gapminder.xlsx')

# 計算 2002 年全球人口各國平均數
avg_pop_2002 = df[df['year'] == 2002]['pop'].mean()

# 計算 2002 年全球各洲平均壽命、平均財富
avg_lifeExp_gdpPercap_2002 = df[df['year'] == 2002].groupby('continent')[['lifeExp', 'gdpPercap']].mean()

print('2002 年全球人口各國平均數:', avg_pop_2002)
print('2002 年全球各洲平均壽命、平均財富:')
print(avg_lifeExp_gdpPercap_2002)