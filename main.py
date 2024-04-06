from fastapi import Request, Depends, FastAPI, APIRouter, HTTPException
from fastapi.responses import HTMLResponse, RedirectResponse, JSONResponse
from fastapi.openapi.docs import get_swagger_ui_html
from fastapi.staticfiles import StaticFiles
from fastapi.encoders import jsonable_encoder
from contextlib import asynccontextmanager
from sqlalchemy.ext.asyncio import AsyncSession
from sqlalchemy.ext.declarative import declarative_base
from sqlalchemy.orm import Session
from typing import List

from query import get_details

import base
import service
import httpx


@asynccontextmanager
async def lifespan(app: FastAPI):
    app.requests_client = httpx.AsyncClient()
    yield
    await app.requests_client.aclose()


app = FastAPI(docs_url=None, redoc_url=None, version='0.0.1', title='Busradar API', summary='tbd.', lifespan=lifespan)
Base = declarative_base()

router = APIRouter(prefix='/busradar/v1')

app.mount('/static', StaticFiles(directory='static'), name='static')


@app.on_event('startup')
async def init_schemas():
    async with base.engine.begin() as conn:
        await conn.run_sync(Base.metadata.drop_all)
        await conn.run_sync(Base.metadata.create_all)


# Dependency
async def get_session() -> AsyncSession:
    async with base.async_session() as session:
        yield session


@app.get('/', include_in_schema=False)
def home_redirect():
    return RedirectResponse('/docs')


@app.get('/docs', include_in_schema=False)
async def swagger_ui_html(req: Request) -> HTMLResponse:
    return get_swagger_ui_html(
        title=app.title,
        openapi_url='/openapi.json',
        swagger_favicon_url='/static/favicon.ico'
    )



@router.get('/details', tags=['Busradar'])
async def get_led(request: Request, session: AsyncSession = Depends(get_session)):
    client = request.app.requests_client
    response = await get_details(client, ['1', '7'])

    output = []

    for res in response:
        rows = await service.get_led(session, float(res['lat']), float(res['lon']))
        led = jsonable_encoder(rows)
        line = res['bus']
        color = [l['color'] for l in base.lines if l['line'] in str(line)]

        output.append({'led': led[0], 'color': color[0], 'line': line})

    return JSONResponse(content=output)


app.include_router(router)
