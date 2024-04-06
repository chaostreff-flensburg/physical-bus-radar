DROP TABLE IF EXISTS routes;

CREATE TABLE IF NOT EXISTS routes(
  id SERIAL PRIMARY KEY,
  route_point geometry(Point, 4326)
);

INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8170392000)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8165554754)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8160717451)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8155880089)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8151042669)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8146205192)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8141367657)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8136530063)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216832000 54.8131692412)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216499496 54.8126859987)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216066973 54.8122028651)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4215660579 54.8117196971)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4216084529 54.8112369833)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4217339002 54.8107587230)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4218732915 54.8102816473)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4220300685 54.8098063529)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4221868324 54.8093310514)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4223436453 54.8088557498)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4225003963 54.8083804357)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4226571623 54.8079051177)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4228139528 54.8074297968)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4229707613 54.8069544723)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4231275254 54.8064791373)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4232843026 54.8060037982)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4234410620 54.8055284515)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4235978471 54.8050531021)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4237543712 54.8045777185)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4239106590 54.8041023034)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4240681471 54.8036270149)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4242249961 54.8031516501)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4243738129 54.8026754764)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4243879389 54.8021936045)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4242875426 54.8017140189)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4239741605 54.8013659141)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4236060230 54.8009312862)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4232501822 54.8004929896)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4228640871 54.8000633335)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4232160296 54.7996638118)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4237779791 54.7993042851)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4243476737 54.7989488729)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4249175039 54.7985935380)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4254928928 54.7982411362)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4260760334 54.7978931168)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4266765366 54.7975549193)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4272770785 54.7972167418)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4278768148 54.7968780871)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4284763047 54.7965392844)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4290767737 54.7962010554)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4296772427 54.7958628236)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4302998173 54.7958524050)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4308930174 54.7960556028)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4314896600 54.7957151270)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4320896478 54.7953767928)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4325486258 54.7949743712)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4328439905 54.7945214033)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4331327243 54.7940669612)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4334169180 54.7936118670)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4335474449 54.7931354899)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4335672882 54.7926518164)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4336095171 54.7921694249)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4336215391 54.7916855258)', 4326));
INSERT INTO routes(route_point) VALUES (ST_GeomFromText('POINT(9.4336719955 54.7912024519)', 4326));
