import pandas as pd

df = pd.read_json("bike.json", encoding='utf8')
result = df[df['bemp'].astype(int) >= 10]

print(result[['sarea', 'sna', 'ar', 'bemp']])
print(result['sarea'].value_counts())
print(result.groupby('sarea')['bemp'].sum())