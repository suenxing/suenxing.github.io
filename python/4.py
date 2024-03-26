import pygame.midi as pm
import time
import random

pm.init()  # init midi player
player = pm.Output(0)
BPM = 120


def note(pitch: int = 60, length: float = 2, velocity: int = 127, instrument: str = 'Piano'):
    if instrument == 'Piano':
        player.set_instrument(0)
    player.note_on(pitch, velocity)
    time.sleep(length * 60 / BPM)
    player.note_off(pitch, velocity)


for x in range(0, 127):
    note(pitch=random.randint(50, 100), length=1)


del player
pm.quit()
