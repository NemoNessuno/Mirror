MOVE_FORWARD = 0
MOVE_TOP = 1
MOVE_RIGHT = 2
MOVE_LEFT = 3
MOVE_BACK = 4
MOVE_DOWN = 5
ROTATE_RIGHT = 6
ROTATE_LEFT = 7
TILT_FRONT = 8
TILT_BACK = 9
STOP = 'a'

basic_movement = [
    [MOVE_TOP, .83],     [STOP, 1.71], [MOVE_DOWN, .97],  [STOP, 1],
    [MOVE_RIGHT, 1],     [STOP, 1],    [MOVE_LEFT, .92],  [STOP, 1.11],
    [ROTATE_RIGHT, .98], [STOP, 1.9],  [ROTATE_LEFT, 1],  [STOP, 1.03],
    [TILT_BACK, 1.16],   [STOP, 1],    [TILT_FRONT, .96]
]

rhythm_movement = [
    [MOVE_FORWARD, .2], [STOP, .2], [MOVE_FORWARD, .2], [STOP, .4], [MOVE_BACK, .2]
]

tutor_movement = [
    [MOVE_FORWARD, .4], [MOVE_RIGHT, .4], [MOVE_BACK, .4], [MOVE_LEFT, .4],
    [MOVE_FORWARD, .4], [MOVE_RIGHT, .4], [MOVE_BACK, .4], [MOVE_LEFT, .4]
]

basic_choreo = [[STOP, 23.5]] + basic_movement + [[STOP, 1]]
rhythm_choreo = [[STOP, 24]] + rhythm_movement + [[STOP, 1]]
tutor_choreo = [[STOP, 22]] + tutor_movement + [[STOP, 1]]