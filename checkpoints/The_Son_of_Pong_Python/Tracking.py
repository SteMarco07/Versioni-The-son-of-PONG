import cv2
import mediapipe as mp
import math

from Mano import calcola_distanza

# Inizializza MediaPipe e OpenCV
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_draw = mp.solutions.drawing_utils

# Funzione per calcolare la distanza euclidea tra due punti
def calculate_distance(point1, point2):
    return math.sqrt((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)

# Funzione per calcolare il threshold dinamico
def fai_la_proporzione(threshold_reale, distanza_reale, distanza_misurata):
    return (threshold_reale * distanza_misurata) / distanza_reale

# Funzione per rilevare il gesto del palmo aperto
def is_open_hand(landmarks, distance):
    # Punti chiave della mano
    thumb_tip = landmarks[4]  # Pollice
    index_tip = landmarks[8]  # Indice
    middle_tip = landmarks[12]  # Medio
    ring_tip = landmarks[16]  # Anulare
    pinky_tip = landmarks[20]  # Mignolo

    # Distanza tra il pollice e le altre dita
    thumb_index_dist = calculate_distance(thumb_tip, index_tip)
    index_middle_dist = calculate_distance(index_tip, middle_tip)
    middle_ring_dist = calculate_distance(middle_tip, ring_tip)
    ring_pinky_dist = calculate_distance(ring_tip, pinky_tip)

    # Calcola un threshold dinamico basato sulla distanza
    dynamic_threshold = fai_la_proporzione(0.075, 0.2, distance)  # 0.2 è una distanza di riferimento

    # Se tutte le distanze sono superiori al threshold dinamico, la mano è considerata aperta
    if (thumb_index_dist > dynamic_threshold and
            index_middle_dist > dynamic_threshold and
            middle_ring_dist > dynamic_threshold and
            ring_pinky_dist > dynamic_threshold):
        return True
    return False



# Inizializza la videocamera
cap = cv2.VideoCapture(0)

# Imposta la risoluzione desiderata
larghezza = 640  # Larghezza del frame
altezza = 480  # Altezza del frame
cap.set(cv2.CAP_PROP_FRAME_WIDTH, larghezza)
cap.set(cv2.CAP_PROP_FRAME_HEIGHT, altezza)

while True:
    ret, frame = cap.read()
    if not ret:
        break

    # Converte il frame in RGB
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Esegui il rilevamento delle mani
    results = hands.process(frame_rgb)

    # Disegna i punti di riferimento e verifica se la mano è aperta
    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            # Calcola la distanza tra il polso (landmark 0) e il dito medio (landmark 9) come riferimento
            polso = hand_landmarks.landmark[0]
            punta_medio = hand_landmarks.landmark[12]
            distanza = calcola_distanza(polso, punta_medio)

            # Verifica se il gesto è un palmo aperto
            distanza = distanza * altezza
            if distanza > 125:
                print("APERTA")

            # Disegna le mani sulla scena
            mp_draw.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)

    # Mostra il frame
    frame = cv2.flip(frame, 1)
    cv2.imshow("Palm Gesture Detection", frame)

    # Esci se premi la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Rilascia la videocamera e chiudi le finestre
cap.release()
cv2.destroyAllWindows()
