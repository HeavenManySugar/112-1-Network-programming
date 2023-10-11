import requests
from bs4 import BeautifulSoup
import pandas as pd

def earthquake_scraper(url):
    response = requests.get(url)
    soup = BeautifulSoup(response.text, 'html.parser')

    # 找到所有的地震資訊
    earthquakes = soup.find_all('tr', class_='btnInfo')

    # 建立一個空的DataFrame來儲存資訊
    df = pd.DataFrame(columns=['地震時間', '深度', '規模', '地震位置'])

    for quake in earthquakes:
        tmp = quake.find_all('td', string=True)
        time = tmp[0].text.strip()
        magnitude = tmp[1].text.strip()
        depth = tmp[2].text.strip()
        location = tmp[3].text.strip()
        # print(time, magnitude,depth,location)
        # 將資訊加入DataFrame
        df = df._append({'地震時間': time, '深度': depth, '規模': magnitude, '地震位置': location}, ignore_index=True)

    # 依照規模和深度排序並取前三筆
    df = df.sort_values(by=['規模', '深度']).head(3)

    return df

# 使用方式
df = earthquake_scraper('https://scweb.cwa.gov.tw/')
print(df)
