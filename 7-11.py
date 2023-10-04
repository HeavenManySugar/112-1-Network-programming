#抓取7-eleven各門市資訊
import requests #抓取網頁的套件
import pandas as pd #分析資料的套件
import re
from io import StringIO

def extract_street(address):
    match = re.search(r'(\w+路|\w+街)', address)
    return match.group(0) if match else None

# 建立一個縣市的list
city = ['基隆市', '台北市', '新北市', '桃園市']
#city = ['基隆市', '台北市', '新北市', '桃園市', '新竹市','新竹縣','苗栗縣','台中市','彰化縣', '雲林縣', '南投縣', '嘉義縣', '嘉義市', '台南市', '高雄市', '屏東縣', '台東縣', '花蓮縣', '宜蘭縣', '連江縣', '金門縣', '澎湖縣']
#使用迴圈依序取得每一個城市的門市資訊， enumerate(city) 產生 [0, 基隆市] [1, 台北市][2, 新北市][3, 桃園市]
for index, city in enumerate(city): 
    #剛在網頁開發者模式觀察到的Post發出的資訊是那些
    data = {'strTargetField':'COUNTY','strKeyWords':'%s' % city}
    #res 取得網頁所有資料
    res = requests.post('https://www.ibon.com.tw/retail_inquiry_ajax.aspx', data=data)
    # 使用StringIO對象包裹HTML字符串
    html_io = StringIO(res.text)
    # 第一次迴圈，建立 df_7_11_store 字典資料
    if index == 0:
        #網頁資料的形式是table，使用panda的 read_html 取得資料 [0]第一欄資料
        # res.txt 網頁資料中的文字，[0]第一欄資料, header=0 不要第一列標頭資料
        df_7_11_store = pd.read_html(html_io, header=0)[0]
        #建立dataframe，將城市填入。
        df_7_11_store['縣市'] = city
    # 第二次之後迴圈，將oneCity_store 資料 append到df_7_11_store 字典資料 (dataframe)裡
    if index > 0:
        oneCity_store = pd.read_html(html_io, header=0)[0]
        oneCity_store['縣市'] = city
        df_7_11_store = pd.concat([df_7_11_store, oneCity_store])
        #print(oneCity_store) 
    #印出查詢資料進度, shape[0] 查詢本次城市取得資料的筆數
    print('%2d) %-*s %4d' % (index+1, 5, city, pd.read_html(html_io, header=0)[0].shape[0]))
# 提取街道名稱
df_7_11_store['街/路'] = df_7_11_store['地址'].apply(extract_street)

# 計算每條街/路的店鋪數量
street_counts = df_7_11_store['街/路'].value_counts()

# 找出店鋪數量最多的前三名
top_three_streets = street_counts.nlargest(3)

print(top_three_streets)
#將資料輸出成Excel
#df_7_11_store.to_excel('7_11.xlsx', index=False)
