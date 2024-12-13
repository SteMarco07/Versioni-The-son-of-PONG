import cv2
import mediapipe as mp


class Mano:
    def __init__(self, min_detection_confidence=0.7, min_tracking_confidence=0.7):
        self.mp_hands = mp.solutions.hands
        self.hands = self.mp_hands.Hands(
            min_detection_confidence=min_detection_confidence,
            min_tracking_confidence=min_tracking_confidence
        )
        self.mp_draw = mp.solutions.drawing_utils

    def __is_open_hand(self, landmarks):
        # calcola la distanza fra le dita
        punta_pollice = landmarks[4]
        punta_indice = landmarks[8]
        punta_medio = landmarks[12]
        punta_anulare = landmarks[16]
        punta_mignolo = landmarks[20]

        # Calcola le distanze tra le dita
        distanza_poll_ind = cv2.norm((punta_pollice.x, punta_pollice.y), (punta_indice.x, punta_indice.y), cv2.NORM_L2)
        distanza_ind_medio = cv2.norm((punta_indice.x, punta_indice.y), (punta_medio.x, punta_medio.y), cv2.NORM_L2)
        middle_ring_dist = cv2.norm((punta_medio.x, punta_medio.y), (punta_anulare.x, punta_anulare.y), cv2.NORM_L2)
        ring_pinky_dist = cv2.norm((punta_anulare.x, punta_anulare.y), (punta_mignolo.x, punta_mignolo.y), cv2.NORM_L2)

        # Soglia per considerare le dita separate
        threshold = 0.075 / 2
        return (
                distanza_poll_ind > threshold and
                distanza_ind_medio > threshold and
                middle_ring_dist > threshold and
                ring_pinky_dist > threshold
        )

    def rileva_gesto(self, frame):
        """
        Analizza il frame e determina se la mano è aperta.
        Restituisce "APERTO" se il palmo è aperto, altrimenti None.
        """
        # Converte il frame in RGB per Mediapipe
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        # Esegui il rilevamento delle mani
        results = self.hands.process(frame_rgb)

        # Controlla se sono state rilevate mani
        if results.multi_hand_landmarks:
            for landmarks in results.multi_hand_landmarks:
                # Disegna le connessioni sul frame
                self.mp_draw.draw_landmarks(frame, landmarks, self.mp_hands.HAND_CONNECTIONS)

                # Controlla se la mano è aperta
                if self.__is_open_hand(landmarks.landmark):
                    return "APERTO"

        return None


# Esempio di utilizzo della classe Mano
if __name__ == "__main__":
    mano = Mano()
    cap = cv2.VideoCapture(0)

    # Imposta la risoluzione della webcam
    larghezza = 640
    altezza = 480
    cap.set(cv2.CAP_PROP_FRAME_WIDTH, larghezza)
    cap.set(cv2.CAP_PROP_FRAME_HEIGHT, altezza)

    while True:
        ret, frame = cap.read()
        if not ret:
            break

        # Ridimensiona il frame per visualizzazione
        frame = cv2.resize(frame, None, fx=0.5, fy=0.5, interpolation=cv2.INTER_AREA)

        # Rileva il gesto
        gesto = mano.rileva_gesto(frame, cam_resolution=(larghezza, altezza))
        if gesto == "APERTO":
            print("ALTOLA")

        # Mostra il frame
        frame = cv2.flip(frame, 1)
        cv2.imshow("Palm Gesture Detection", frame)

        # Esci se premi 'q'
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Rilascia la videocamera e chiudi le finestre
    cap.release()
    cv2.destroyAllWindows()
