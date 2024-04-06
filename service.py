from sqlalchemy import select
from sqlalchemy.sql import text
from sqlalchemy.ext.asyncio import AsyncSession


async def get_led(session: AsyncSession, lat: float, lon: float):
    stmt = text('''
        SELECT id, ST_Distance(route_point, ST_SetSRID(ST_Point(:lon, :lat), 4326)) AS nearest, ST_X(route_point), ST_Y(route_point)
        FROM routes ORDER BY nearest LIMIT 1;
    ''')

    sql = stmt.bindparams(lat=lat, lon=lon)
    result = await session.execute(sql)

    return result.scalars().all()
