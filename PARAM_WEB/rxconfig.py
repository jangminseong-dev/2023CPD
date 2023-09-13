import reflex as rx

class ParamwebConfig(rx.Config):
    pass

config = ParamwebConfig(
    app_name="PARAM_WEB",
    api_url="http://param.minstar.kr:8000"
)