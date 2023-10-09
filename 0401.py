import pandas as pd
import numpy as np

student = {
    'id': ['1', '2', '3', '4'],
    'name': ['Amy', 'Bob', 'Cathy', 'David'],
    'cs': np.random.randint(60, 100, 4),
    'pd': np.random.randint(60, 100, 4),
}

df = pd.DataFrame(student)
df['rank'] = df['cs'] + df['pd']

df['rank'] = df['rank'].rank().astype(int)

print(df[df['cs'] >= 60])
print(df[df['cs'] >= 50][['name', 'pd']])