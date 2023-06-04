import pynecone as pc
import WEB


def navbar():
    return pc.box(
        pc.hstack(
            pc.hstack(
                pc.image(src="/logo.png", width="50px"),
                pc.heading("파람 중앙제어 시스템"),
                pc.flex(
                    pc.badge("Ver2023.06.002", color_scheme="blue"),
                ),
            ),
            justify="space-between",
            border_bottom="0.2em solid #F0F0F0",
            padding_x="2em",
            padding_y="1em",
            bg="rgba(255,255,255, 0.97)",
        ),
        position="fixed",
        width="100%",
        top="0px",
        z_index="500",
    )