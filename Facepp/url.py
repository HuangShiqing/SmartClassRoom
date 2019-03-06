# -*- coding: utf-8 -*-
import urllib.request
import urllib.error
import time
import json


def url_detect(filepath):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/detect'
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    fr = open(filepath, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    # data.append('--%s' % boundary)
    # data.append('Content-Disposition: form-data; name="%s"\r\n' % 'return_landmark')
    # data.append('1')
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'return_attributes')
    data.append("headpose,facequality,eyegaze")
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_compare(filepath1, filepath2, face_rectangle1=None, face_rectangle2=None):
    # "top，left，width，height"
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/compare'
    # 免费
    # key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    # secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'

    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    fr = open(filepath1, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file1')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    data.append('--%s' % boundary)
    fr = open(filepath2, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file2')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()

    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_rectangle1')
    data.append('{},{},{},{}'.format(face_rectangle1['top'], face_rectangle1['left'], face_rectangle1['width'],
                                     face_rectangle1['height']))
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_rectangle2')
    data.append('{},{},{},{}'.format(face_rectangle2['top'], face_rectangle2['left'], face_rectangle2['width'],
                                     face_rectangle2['height']))

    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_create(outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/create'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_getdetail(outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/getdetail'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_faceset_add(outer_id, face_tokens):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/faceset/addface'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'face_tokens')
    data.append(face_tokens)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


def url_search(filepath, outer_id):
    http_url = 'https://api-cn.faceplusplus.com/facepp/v3/search'
    # 免费
    key = "q77EK-wF9dqlqqZAJKWEml_qki2GNTS1"
    secret = "WhXup4yLMc8OQF99mQ90DlV7p-hfYe46"
    # 收费
    # key = 'lMA4mtztEo3rqCA1IKDBYPhX_w3fWvY4'
    # secret = 'c8xugTC1ECKYM1K_FPjPWeNZuqEJZUFU'
    boundary = '----------%s' % hex(int(time.time() * 1000))
    data = []
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_key')
    data.append(key)
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'api_secret')
    data.append(secret)

    data.append('--%s' % boundary)
    fr = open(filepath, 'rb')
    data.append('Content-Disposition: form-data; name="%s"; filename=" "' % 'image_file')
    data.append('Content-Type: %s\r\n' % 'application/octet-stream')
    data.append(fr.read())
    fr.close()
    data.append('--%s' % boundary)
    data.append('Content-Disposition: form-data; name="%s"\r\n' % 'outer_id')
    data.append(outer_id)
    data.append('--%s--\r\n' % boundary)

    for i, d in enumerate(data):
        if isinstance(d, str):
            data[i] = d.encode('utf-8')
    http_body = b'\r\n'.join(data)
    # build http request
    req = urllib.request.Request(url=http_url, data=http_body)
    # header
    req.add_header('Content-Type', 'multipart/form-data; boundary=%s' % boundary)
    try:
        # post data to server
        resp = urllib.request.urlopen(req, timeout=5)
        # get response
        qrcont = resp.read()
        # if you want to load as json, you should decode first,
        # for example: json.loads(qrount.decode('utf-8'))
        print(qrcont.decode('utf-8'))
        data = eval(qrcont.decode('utf-8'))
        with open('data.json', 'w') as json_file:
            json_file.write(json.dumps(data))
    except urllib.error.HTTPError as e:
        print(e.read().decode('utf-8'))


if __name__ == '__main__':
    # pitch_angle越大，低头越严重，大于10就认为是低头
    # facequality越大那么脸越清晰，越能证明抬头（不太准）
    # vector_z_component越大越认真，大于0.9就认为是向上
    url_detect('../img/model/j/jbad7.jpg')

    # face_rectangle1 = {"width": 181, "top": 155, "left": 94, "height": 181}
    # face_rectangle2 = {"width": 121, "top": 205, "left": 449, "height": 121}
    # url_compare('../img/t1.jpg', '../img/t4.jpg', face_rectangle1, face_rectangle2)

    # url_faceset_create(outer_id='faceset_test')
    # url_faceset_getdetail(outer_id='faceset_test')
    # url_faceset_add(outer_id='faceset_test',
    #                 face_tokens='32f4b716dccb632139d33e3b0fbe99a9,2476e3a308dafd3ac987cc237836e9b7')  # 佟丽娅、吴京的face_token
    # url_search('../img/t2.jpg', outer_id='faceset_test')
    exit()
