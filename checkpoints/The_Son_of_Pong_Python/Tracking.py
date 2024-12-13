import cv2
import mediapipe as mp

# Inizializza MediaPipe e OpenCV
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.7, min_tracking_confidence=0.7)
mp_draw = mp.solutions.drawing_utils


def fai_la_proporzione(threshold_reale, distanza_reale, distanza_misurata):
    threshold_reale = float(threshold_reale)
    distanza_reale = float(distanza_reale)
    distanza_misurata = float(distanza_misurata)
    # T_R : D_R = X : D_M quindi X = T_R*D_M / D_R
    return (threshold_reale * distanza_misurata) / distanza_reale


# Funzione per rilevare il gesto del palmo aperto
def is_open_hand(landmarks):
    # Controlliamo la distanza tra il polso e le dita per determinare se la mano è aperta
    # La mano è considerata aperta se tutte le dita sono ben separate.

    # I punti di riferimento delle dita sono dati dai landmarks
    # Indici delle dita da verificare (0 è il polso, 1 è il pollice, 5 è il mignolo, ecc.)
    thumb_tip = landmarks[4]  # Pollice
    index_tip = landmarks[8]  # Indice
    middle_tip = landmarks[12]  # Medio
    ring_tip = landmarks[16]  # Anulare
    pinky_tip = landmarks[20]  # Mignolo

    # Distanza tra il pollice e l'indice (vediamo se è sufficientemente separato)
    thumb_index_dist = cv2.norm((thumb_tip.x, thumb_tip.y), (index_tip.x, index_tip.y), cv2.NORM_L2)
    index_middle_dist = cv2.norm((index_tip.x, index_tip.y), (middle_tip.x, middle_tip.y), cv2.NORM_L2)
    middle_ring_dist = cv2.norm((middle_tip.x, middle_tip.y), (ring_tip.x, ring_tip.y), cv2.NORM_L2)
    ring_pinky_dist = cv2.norm((ring_tip.x, ring_tip.y), (pinky_tip.x, pinky_tip.y), cv2.NORM_L2)

    # Se tutte le distanze tra le dita sono superiori a una certa soglia, consideriamo la mano aperta
    threshold = 0.075 / 2  # Può essere modificato in base alla tua applicazione
    if (thumb_index_dist > threshold and
            index_middle_dist > threshold and
            middle_ring_dist > threshold and
            ring_pinky_dist > threshold):
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

    frame = cv2.resize(frame, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_AREA)

    # Converte il frame in RGB
    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

    # Esegui il rilevamento delle mani
    results = hands.process(frame_rgb)

    # Disegna i punti di riferimento e verifica se la mano è aperta
    if results.multi_hand_landmarks:
        for landmarks in results.multi_hand_landmarks:
            # Verifica se il gesto è un palmo aperto
            if is_open_hand(landmarks.landmark):
                print(f"ALTOLA")

            # Disegna le mani sulla scena
            mp_draw.draw_landmarks(frame, landmarks, mp_hands.HAND_CONNECTIONS)

    frame = cv2.flip(frame, 1)
    # Mostra il frame
    cv2.imshow("Palm Gesture Detection", frame)

    # Esci se premi la tecla 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

# Rilascia la videocamera e chiudi le finestre
cap.release()
cv2.destroyAllWindows()
