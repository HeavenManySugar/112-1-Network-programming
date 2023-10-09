import json
import requests
import pandas as pd
from sqlalchemy import create_engine # 需使用SQLAlchemy==1.4.46
#環保署開放資料API網址,用requests的get方法取得檔案,設為req物件

req = requests.get('https://data.moenv.gov.tw/api/v2/aqx_p_432?api_key=e8dd42e6-9b8b-43f8-991e-b3dee723a52d&limit=1000&sort=ImportDate%20desc&format=JSON')

# loads方法解析req物件,存為data物件
data = json.loads(req.content.decode('utf8'))
df = pd.DataFrame(data['records']) #解析為pandas的DataFrame結構
# 用sqlalchemy模組create_engine建立sqlite連線,將資料表儲存在memory
engine = create_engine('sqlite:///:memory:')    
# 將df利用to_sql方法指定給'AQI_table'   
# 用SQL語法顯示縣市、區域、PM2.5,並以PM2.5排序
df.to_sql('AQI_table', engine, index=False)
input_county = input('請輸入縣市名稱:')
input_pm25 = input('請輸入PM2.5數值:')
print(pd.read_sql_query(f'SELECT `County` as `縣市`, `SiteName` as `區域`, \
AQI as `空氣品質指標`, `PM2.5_AVG` as `細懸浮微粒移動平均值（μg/m3）`, \
Status as `狀態` FROM `AQI_table` \
WHERE `County` = "{input_county}" AND `PM2.5_AVG` > {input_pm25} \
order by `PM2.5_AVG` DESC', engine))