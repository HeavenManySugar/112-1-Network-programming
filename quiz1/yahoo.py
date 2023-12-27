import requests as rq
from bs4 import BeautifulSoup

url="https://tw.stock.yahoo.com/tw-etf/volume" #網址
html=rq.get(url) # 讀取靜態網頁 html
html.raise_for_status() # 若沒讀到網頁，回傳error
#print(html.text) # 輸出讀取到的 html
soup = BeautifulSoup(html.text,"html.parser") #內建parser分析轉成BeautifulSoup物件
name = soup.find_all("div",class_="D(f) Start(0) H(100%) Ai(c) Bgc(#fff) table-row:h_Bgc(#e7f3ff) Pstart(12px) Pend(12px) Bdrststart(4px) Bdrsbstart(4px) Pos(r) Bxz(bb) Z(2)")
j = 0

dic = {}
result = []

for n in name:
    if j == 10: break
    j += 1
    # print(f"Loading {n.text}...")

    html=rq.get(f"{n.find('a').get('href')}/performance") # 讀取靜態網頁 html
    html.raise_for_status() # 若沒讀到網頁，回傳error
    soup = BeautifulSoup(html.text,"html.parser") #內建parser分析轉成BeautifulSoup物件
    tmp = soup.find_all("span",class_="Fw(600)")[0]
    tmp = ('-'+tmp.text if "C($c-trend-down)" in tmp['class'] else tmp.text)
    dic[n.find('span', class_="Fz(14px) C(#979ba7) Ell").text] = tmp
    
for item in dic:
    result.append([dic[item], item])
result.sort(reverse=True, key=lambda x: float(x[0][:-1]) if x[0][-1] == '%' else float(x[0]))
for i in range(3):
    print(result[i][1], result[i][0])
