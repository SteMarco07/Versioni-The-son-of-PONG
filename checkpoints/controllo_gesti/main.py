import cv2 as cv
import mediapipe as mp
from mediapipe.tasks import python
from mediapipe.tasks.python import vision

# STEP 1: Configura il modello di Gesture Recognition
base_options = python.BaseOptions(model_asset_path='gesture_recognizer.task')
options = vision.GestureRecognizerOptions(base_options=base_options)
recognizer = vision.GestureRecognizer.create_from_options(options)

# STEP 2: Inizializza la webcam
cap = cv.VideoCapture(0)

if not cap.isOpened():
    print("Errore nell'apertura della webcam")
    exit()

print("Premi 'q' per uscire.")

while True:
    ret, frame = cap.read()
    if not ret:
        print("Errore nel leggere il frame dalla webcam")
        break

    frame = cv.flip(frame, 1)

    # STEP 3: Converti il frame in formato richiesto da Mediapipe
    frame_rgb = cv.cvtColor(frame, cv.COLOR_BGR2RGB)
    mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame_rgb)

    # STEP 4: Riconosci i gesti
    recognition_result = recognizer.recognize(mp_image)

    # STEP 5: Estrai e stampa il gesto principale
    if recognition_result.gestures and len(recognition_result.gestures[0]) > 0:
        top_gesture = recognition_result.gestures[0][0]
        if top_gesture.category_name != "None":
            print(f"Gesto riconosciuto: {top_gesture.category_name}")

    # STEP 6: Mostra il frame catturato dalla webcam
    cv.imshow('Webcam', frame)

    # Esci premendo 'q'
    if cv.waitKey(1) & 0xFF == ord('q'):
        break

# Rilascia risorse
cap.release()
cv.destroyAllWindows()
