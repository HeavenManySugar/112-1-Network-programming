import urllib.request   
import zipfile
import csv

url = "https://data.ntpc.gov.tw/api/datasets/71CD1490-A2DF-4198-BEF1-318479775E8A/csv/zip"
zipName = "data.zip"

urlretrieve = urllib.request.urlretrieve(url, zipName)
f = zipfile.ZipFile(zipName)
for file in f.namelist():
    f.extract(file, "./")
    fileName = file
f.close()

f = open(file, "r", encoding="utf-8")
plots = csv.reader(f, delimiter=",")
# sno[0], sna[1], tot[2], sbi[3], ar[8], bemp[12]
i = 0
for row in plots:
    if i == 0:
        i += 1
        continue
    if int(row[12]) > 4:
        print(f'{row[0]:5s}{row[1]:15s}{row[2]:5s}{row[3]:5s}{row[8]:15s}{row[12]:5s}')

f.close()
