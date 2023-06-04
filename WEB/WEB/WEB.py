import pynecone as pc
from .header import navbar

class State(pc.State):
    settings : bool = False
    
    def ShowSettings(self):
        self.settings = not (self.settings)
    pass


def index() -> pc.Component:
    return pc.tablet_and_desktop(
            pc.vstack(
                navbar(),
                pc.grid(
                    pc.box(pc.hstack(pc.heading("MP-001", size="lg"), pc.badge("Connected", color_scheme="green")),
                            pc.hstack(pc.stat(pc.stat_number("25°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("57%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("1㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("27ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"), on_click=State.ShowSettings)),
                            bg="white", w="300px", border_radius="7px", padding="10px", box_shadow="1px 3px 0 rgba(0, 0, 0, 0.1),0 1px 2px 0 rgba(0, 0, 0, 0.06)"
                            ),
                    pc.box(pc.hstack(pc.heading("MP-002", size="lg"), pc.badge("Disconnected", color_scheme="red")),
                            pc.hstack(pc.stat(pc.stat_number("--°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("--%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("--㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("--ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"))),
                            bg="white", w="300px", border_radius="7px", padding="10px", box_shadow="1px 3px 0 rgba(0, 0, 0, 0.1),0 1px 2px 0 rgba(0, 0, 0, 0.06)"
                            ),
                    pc.box(pc.hstack(pc.heading("MP-003", size="lg"), pc.badge("Disconnected", color_scheme="red")),
                            pc.hstack(pc.stat(pc.stat_number("--°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("--%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("--㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("--ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"))),
                            bg="white", w="300px", border_radius="7px", padding="10px", box_shadow="1px 3px 0 rgba(0, 0, 0, 0.1),0 1px 2px 0 rgba(0, 0, 0, 0.06)"
                            ),
                    template_rows="repeat(10, 1fr)",
                    template_columns="repeat(7, 1fr)",
                    gap=4,
                    height="90vh",
                    width="100%",
                    padding="10px"
                ),
                margin_top="78px",
            ),
            pc.modal(
                pc.modal_overlay(
                    pc.modal_content(
                        pc.modal_header("기기 환경설정"),
                        pc.modal_body(
                                pc.tabs(
                                    pc.tab_list(
                                        pc.tab("시간표 설정"),
                                        pc.tab("기기 환경설정"),
                                    ),
                                    pc.tab_panels(
                                        pc.tab_panel(
                                                pc.table_container(
                                                                    pc.table(
                                                                        headers=["시간", "월", "화", "수", "목", "금"],
                                                                        rows=[
                                                                            ("아침조회", "", "", "", "" , ""),
                                                                            ("1교시", "자율", "과학", "수학", "사회", "영어"),
                                                                            ("2교시", "미술", "수학", "국어", "실험", "기가"),
                                                                            ("3교시", "미술", "기가", "한국사", "한국사", "체육"),
                                                                            ("4교시", "수학", "영어", "체육", "국어", "국어"),
                                                                            ("점심시간", "", "", "", "", ""),
                                                                            ("5교시", "한국사", "보건", "영어", "과학", "사회"),
                                                                            ("6교시", "과학", "국어", "진로", "수학", "동아리"),
                                                                            ("7교시", "진로", "사회", "", "영어", "동아리"),
                                                                        ],
                                                                        variant="striped",
                                                                    )
                                                                )
                                            ),
                                        pc.tab_panel(pc.heading("페이지 준비중")),
                                    ),
                                    )
                        ),
                        pc.modal_footer(pc.spacer(), pc.button("닫기", on_click=State.ShowSettings))
                    )
                ),
                is_open=State.settings,
                size="3xl"
            ),
            w="100%",
        )


# Add state and page to the app.
app = pc.App(state=State)
app.add_page(index)
app.compile()
