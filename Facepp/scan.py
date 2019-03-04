import os
from url import url_detect

list_old = os.listdir('./picture/')
list_mid = None
list_new = None
added_picture = None
while (True):
    temp = os.listdir('./picture/')
    if temp != list_old:
        list_mid = temp
        while (True):
            temp = os.listdir('./picture/')
            if temp != list_mid:
                list_new = os.listdir('./picture/')
                added_picture = list(set(list_mid).difference(set(list_old)))

                url_detect(added_picture[0])
                list_old = list_mid
                list_mid = list_new
                list_new = None

exit()
