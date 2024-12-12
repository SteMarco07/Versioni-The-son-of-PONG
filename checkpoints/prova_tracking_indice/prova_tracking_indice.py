import cv2 as cv
import mediapipe.python.solutions.hands as mp_hands
from pyray import *

cam = cv.VideoCapture(0)
width = 1280
height = 720
cam.set(cv.CAP_PROP_FRAME_WIDTH, width)
cam.set(cv.CAP_PROP_FRAME_HEIGHT, height)


set_target_fps(60)
init_window(0, 0, "Traccia dita")


x1 = 50
x2 = get_screen_width() - 100
altezza = 200
y1 = 0
y2 = 0

hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    min_detection_confidence=0.5
)

while cam.isOpened():
    success, frame = cam.read()
    frame = cv.flip(frame, 1)

    if not success:
        print("Frame della videocamera non disponibile")
        continue

    frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)

    hands_detected = hands.process(frame)


    indici = []

    if hands_detected.multi_hand_landmarks:

        indici = []

        for hand_landmarks in hands_detected.multi_hand_landmarks:
            fingertip = hand_landmarks.landmark[8]
            h, w, _ = frame.shape
            cx, cy = int(fingertip.x * w), int(fingertip.y * h)
            cv.circle(frame, (cx, cy), 10, (0, 255, 0), -1)
            indici.append((fingertip.x, fingertip.y))


        indici.sort(key=lambda pos: pos[0])



        if len(indici) > 0 and 0 < indici[0][1] * get_screen_height() - altezza/ 2 and indici[0][1] * get_screen_height() + altezza/ 2 < get_screen_height():
            y1 = int(indici[0][1] * get_screen_height() - altezza/ 2)

        if len(indici) > 1 and 0 < indici[1][1] * get_screen_height() - altezza/ 2 and indici[1][1] * get_screen_height() + altezza/ 2 < get_screen_height():
            y2 = int(indici[1][1] * get_screen_height() - altezza/ 2)

    # Disegna la finestra
    begin_drawing()
    clear_background(BLACK)

    # Disegna le barrette
    draw_rectangle(x1, y1, 20, altezza, WHITE)
    draw_rectangle(x2, y2, 20, altezza, WHITE)

    end_drawing()

    # Mostra il frame della videocamera
    cv.imshow("FrameVideo", frame)

    # Esci premendo 'q'
    if cv.waitKey(20) & 0xff == ord('q'):
        break

# Rilascia le risorse
cam.release()
close_window()
