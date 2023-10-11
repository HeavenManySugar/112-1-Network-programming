import pandas as pd
import requests
import zipfile
import io

# 下載並解壓縮zip檔案
url = 'https://data.ntpc.gov.tw/api/datasets/34b402a8-53d9-483d-9406-24a682c2d6dc/csv/zip'
response = requests.get(url)
zip_file = zipfile.ZipFile(io.BytesIO(response.content))
zip_file.extractall()

# 讀取csv檔案
csv_file = zip_file.namelist()[0]
df = pd.read_csv(csv_file)

# 計算站位數量
df['num'] = df.groupby('routeId')['routeId'].transform('count')

# 4-1. 篩選出最多站位數量的前五個路線代碼資訊
top5_routes = df.sort_values('num', ascending=False).drop_duplicates('routeId').head(5)
print(top5_routes[['routeId', 'num']])

# 4-2. 篩選出大於或等於N個站位數量的前五個路線代碼資訊
N = int(input())
filtered_routes = df[df['num'] >= N].sort_values('routeId').drop_duplicates('routeId').head(5)
print(filtered_routes[['routeId', 'num']])
