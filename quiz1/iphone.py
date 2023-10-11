from bs4 import BeautifulSoup
import urllib.request
import re

request_url = 'https://www.apple.com/tw/iphone-15-pro/specs/' 
htmlContent = urllib.request.urlopen(request_url).read()
soup = BeautifulSoup(htmlContent, "html.parser")  

results = soup.find_all("div", {"class": {"techspecs-row"}})
for index, item in enumerate(results):
    try:
        title = item.find("div", {"class": {"techspecs-rowheader"}}).text.strip().replace(" ", "")
        content = item.find("div", {"class": {"techspecs-column"}}).text.strip().replace("\n", " ")

        if title[:2] == '外觀':
            pattern = r'(?<=iPhone 15 Pro\s)(.*)(?=\s鈦金屬設計)'
            matches = re.findall(pattern, content)
            print(f'顏色：{matches[0].replace(" ", "")}')
        if title[:2] == '容量':
            pattern = r'(?<=iPhone 15 Pro\s)(.*)'
            matches = re.findall(pattern, content)
            print(f'容量：{matches[0].replace(" ", "").replace("GB", "GB, ")}')
        if title[:2] == '尺寸':
            pattern = r'(?<=iPhone 15 Pro\s)(.*)(?<=\s公克)'
            matches = re.findall(pattern, content)
            print(matches[0].replace(" ", ""))
        if title == "顯示器":
            pattern = r'(?<=顯示器\s)(\d+\.\d+)(?=\s吋)'
            matches = re.findall(pattern, content)
            print(f'螢幕大小：{matches[0]}吋')            
            break
    except:
        pass

