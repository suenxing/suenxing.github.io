import requests as r
import json
import time

bv = 'BV1GP411P7Qx'
l, c, v, f, q, d = 0, 0, 0, 0, 0, 0


def get():
    global data, likes, coins, views, favor, danmaku, reply, bv, output, l, c, v, f, q, d
    data = json.loads(
        r.get(url='https://api.bilibili.com/x/web-interface/view?bvid=' +
              bv).text)['data']

    title = data['title']

    data = data['stat']

    likes = data['like']
    coins = data['coin']
    views = data['view']
    favor = data['favorite']
    reply = data['reply']
    danmaku = data['danmaku']

    output = '''
标题: {}
浏览：{} +{uv}
点赞：{} +{ul}
投币：{} +{uc}
收藏：{} +{uf}
评论：{} +{ur}
弹幕：{} +{ud}
'''.format(title,
           views,
           likes,
           coins,
           favor,
           reply,
           danmaku,
           uv=views - v,
           ul=likes - l,
           uc=coins - c,
           uf=favor - f,
           ur=reply - q,
           ud=danmaku - d)

    l = likes
    c = coins
    v = views
    f = favor
    q = reply
    d = danmaku


while True:
    get()
    print(output)
    time.sleep(300)
