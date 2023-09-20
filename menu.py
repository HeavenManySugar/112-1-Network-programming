import xml.etree.ElementTree as ET
import json

tree = ET.parse('menu.xml')
root = tree.getroot()
newfood = [{"beer": "$15"}, {"skewers": "$20"}, {"barbecue": "$25"}]
root.append(ET.Element("Night snack", {"hours": "21-23"}))
for item in newfood:
    tmp = ET.Element("item", {"price": list(item.values())[0]})
    tmp.text = list(item.keys())[0]
    root.find("Night snack").append(tmp)

xmldict = {}
for item in root:
    xmldict[item.tag] = {}
    for subitem in item:
        xmldict[item.tag][subitem.text] = subitem.attrib["price"]

file=open("menu.json", "w", encoding="utf-8")
json.dump(xmldict, file)
file.close()

#tree.write("menu.xml", encoding="utf-8")