from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.ext.asyncio import create_async_engine
from sqlalchemy.orm import sessionmaker
from functools import lru_cache

import config



@lru_cache()
def get_settings():
    return config.Settings()


lines = [{
    'line': '1',
    'color': get_settings().line_1
},
{
    'line': '2',
    'color': get_settings().line_2
},
{
    'line': '3',
    'color': get_settings().line_3
},
{
    'line': '4',
    'color': get_settings().line_4
},
{
    'line': '5a',
    'color': get_settings().line_5a
},
{
    'line': '5b',
    'color': get_settings().line_5b
},
{
    'line': '7',
    'color': get_settings().line_7
},
{
    'line': '8a',
    'color': get_settings().line_8a
},
{
    'line': '8b',
    'color': get_settings().line_8b
},
{
    'line': '10',
    'color': get_settings().line_10
},
{
    'line': '11',
    'color': get_settings().line_11
},
{
    'line': '12',
    'color': get_settings().line_12
},
{
    'line': '14',
    'color': get_settings().line_14
}]

url_base = get_settings().url_base
url_detail = get_settings().url_detail

username = get_settings().username
password = get_settings().password
database = get_settings().database
port = get_settings().port
host = get_settings().host


DATABASE_URL = f'postgresql+asyncpg://{username}:{password}@{host}:{port}/{database}'


Base = declarative_base()

engine = create_async_engine(DATABASE_URL, echo=True)
async_session = sessionmaker(engine, class_=AsyncSession, expire_on_commit=False)
