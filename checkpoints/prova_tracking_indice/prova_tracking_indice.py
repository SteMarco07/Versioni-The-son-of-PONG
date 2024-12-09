import cv2 as cv
import mediapipe.python.solutions.hands as mp_hands
# import mediapipe.python.solutions.hands_connections as mp_hands_connections
# import mediapipe.python.solutions.drawing_utils as drawing
# import mediapipe.python.solutions.drawing_styles as drawing_styles

cam = cv.VideoCapture(0)

hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=2,
    min_detection_confidence=0.5)

while cam.isOpened():
    success, frame = cam.read()
    frame = cv.flip(frame, 1)

    if not success:
        print("Frame della videocamera non disponibile")
        continue

    frame = cv.cvtColor(frame, cv.COLOR_BGR2RGB)

    hands_detected = hands.process(frame)

    frame = cv.cvtColor(frame, cv.COLOR_RGB2BGR)

    if hands_detected.multi_hand_landmarks:
        for hand_landmarks in hands_detected.multi_hand_landmarks:
            fingertip = hand_landmarks.landmark[8]
            h, w, _ = frame.shape
            cx, cy = int(fingertip.x * w), int(fingertip.y * h)
            cv.circle(frame, (cx, cy), 10, (0, 255, 0), -1)

    cv.imshow("FrameVideo", frame)

    if cv.waitKey(20) & 0xff == ord('q'):
        break

cam.release()
