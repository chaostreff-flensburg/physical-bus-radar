from fake_useragent import UserAgent
from urllib.parse import urlparse

import base
import httpx


ua = UserAgent()
cookies = httpx.Cookies()
url_base = base.url_base
url_detail = base.url_detail


async def request_cookie(client, url_base):
    r = await client.get(url_base, timeout=20)

    if 'set-cookie' in r.headers:
        cookie = r.headers['set-cookie'].split(';')

        if len(cookie) >= 0:
            sec_id = cookie[0].split('=')[1]

            return sec_id


async def request_json(client, url_base, url_detail, cookie):
    domain = urlparse(url_base).netloc

    cookies.set('secId', cookie, domain=domain)
    headers = {'user-agent': ua.random, 'referer': url_base}

    r = await client.get(url_detail, headers=headers, cookies=cookies)

    return r.json()


async def get_details(client, bus_lines):
    cookie = cookies.get('secId')

    if cookies.get('secId') is None:
        cookie = await request_cookie(client, url_base)

    details = await request_json(client, url_base, url_detail, cookie)

    result = [{'lat': d['lat'], 'lon': d['lon'], 'bus': d['line']} for d in details['result'] if str(d['line']) in bus_lines]

    return result
