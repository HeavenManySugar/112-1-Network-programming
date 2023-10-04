import pandas as pd
import numpy as np
rng = np.random.RandomState(66) #產生偽隨機數
df = pd.DataFrame({'key': ['A', 'B', 'A', 'B', 'B', 'A'],
'house': rng.randint(low=1, high=20, size=6),
'gold': rng.randint(low=1, high=20, size=6),})

print(df)
#印出 兩個 column 資料
print(df[['house','gold']])
#印出 key='A'的兩個 column 資料
print(df[df['key']=='A'][['key','gold']])
#印出 gold>12 的三個 column 資料
print(df[df['gold']>12][['key','house','gold']])