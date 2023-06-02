import pynecone as pc
from .header import navbar

class State(pc.State):
    pass


def index() -> pc.Component:
    return pc.tablet_and_desktop(
            pc.vstack(
                navbar(),
                pc.grid(
                    pc.box(pc.heading("MP-001", size="lg"),
                            pc.hstack(pc.stat(pc.stat_number("25°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("57%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("1㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("27ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"))),
                            bg="#f9f9f9", w="300px", border_radius="10px", padding="10px"
                            ),
                    pc.box(pc.heading("MP-002", size="lg"),
                            pc.hstack(pc.stat(pc.stat_number("25°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("57%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("1㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("27ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"))),
                            bg="#f9f9f9", w="300px", border_radius="10px", padding="10px"
                            ),
                    pc.box(pc.heading("MP-003", size="lg"),
                            pc.hstack(pc.stat(pc.stat_number("25°C"), pc.stat_help_text("온도")), pc.stat(pc.stat_number("57%"), pc.stat_help_text("습도"))),
                            pc.hstack(pc.stat(pc.stat_number("1㎛"), pc.stat_help_text("미세먼지")), pc.stat(pc.stat_number("27ppm"), pc.stat_help_text("CO₂"))),
                            pc.hstack(pc.button(pc.icon(tag="sun")), pc.spacer(), pc.button(pc.icon(tag="settings"))),
                            bg="#f9f9f9", w="300px", border_radius="10px", padding="10px"
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
            w="100%",
        )


# Add state and page to the app.
app = pc.App(state=State)
app.add_page(index)
app.compile()
