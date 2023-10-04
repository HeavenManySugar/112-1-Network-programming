import pandas as pd
import numpy as np
rng = np.random.RandomState(66) #產生偽隨機數
df = pd.DataFrame({'key': ['A', 'B', 'A', 'B', 'B', 'A'],
'house': rng.randint(low=1, high=20, size=6),
'gold': rng.randint(low=1, high=20, size=6),})

#以 key 為群組的所有欄位之加總
print(df.groupby('key').sum())
#以 key 為群組的 gold欄位的資料
for i in df.groupby('key')['gold']:
    print(i)
#以 key 為群組的 gold欄位之中位數
print(df.groupby('key')['gold'].median())
for (key, group) in df.groupby('key'):
    print('{0} - {1}'.format(key, group.shape) )