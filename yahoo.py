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
    print(f"Loading {n.text}...")
    if j == 9: break
    j += 1
    html=rq.get(f"{n.find('a').get('href')}/dividend") # 讀取靜態網頁 html
    html.raise_for_status() # 若沒讀到網頁，回傳error
    soup = BeautifulSoup(html.text,"html.parser") #內建parser分析轉成BeautifulSoup物件

    year = soup.find_all("div",class_="D(f) W(84px) Ta(start)")
    txt = soup.find_all("div",class_="Fxg(1) Fxs(1) Fxb(0%) Ta(end) Mend($m-table-cell-space) Mend(0):lc Miw(62px)")
    i=0
    # print(txt)
    tmp = []
    for news in txt:
        if i%2==0: 
            yr = year[i//2].text
            # print(year[i//2].text, end=' ')
            if yr[:4] == "2023":
                tmp.append([])
        i = i + 1
        if i<=2: 
            # print('%s' %(news.text), end=' ') # 標題
            pass
        else: 
            if yr[:4] == "2023":
                tmp[-1].append(news.text)
            # print('%9s' %(news.text), end=' ') # 內容
        # if i%2==0:
        #     print()
    # print(tmp)
    dic[n.text] = tmp
for item in dic:
    total = 0
    for i2 in dic[item]:
        total += float(i2[0])
    result.append([total, item])

result.sort(reverse=True)
for i in range(3):
    print(result[i][1], result[i][0])