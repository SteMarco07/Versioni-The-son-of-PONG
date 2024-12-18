import cv2
import mediapipe as mp
import math

def calcola_distanza(point1, point2):
    return math.sqrt((point1.x - point2.x) ** 2 + (point1.y - point2.y) ** 2)
class Mano:
    def __init__(self, min_detection_confidence=0.7, min_tracking_confidence=0.7):
        self.mp_hands = mp.solutions.hands
        self.hands = self.mp_hands.Hands(
            min_detection_confidence=min_detection_confidence,
            min_tracking_confidence=min_tracking_confidence
        )
        self.mp_draw = mp.solutions.drawing_utils

    def is_aperta(self, frame, altezza=480):

        # Esegui il rilevamento delle mani
        results = self.hands.process(frame)

        # Disegna i punti di riferimento e verifica se la mano è aperta
        if results.multi_hand_landmarks:
            for hand_landmarks in results.multi_hand_landmarks:
                # Calcola la distanza tra il polso (landmark 0) e il dito medio (landmark 9) come riferimento
                polso = hand_landmarks.landmark[0]
                punta_medio = hand_landmarks.landmark[12]
                distanza = calcola_distanza(polso, punta_medio)

                # Verifica se il gesto è un palmo aperto
                distanza = distanza * altezza
                return distanza > 125

    #def rileva_gesto(self, frame):
    #    """
    #    Analizza il frame e determina se la mano è aperta.
    #    Restituisce "APERTO" se il palmo è aperto, altrimenti None.
    #    """
    #    # Converte il frame in RGB per Mediapipe
    #    frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
#
    #    # Esegui il rilevamento delle mani
    #    results = self.hands.process(frame_rgb)
#
    #    # Controlla se sono state rilevate mani
    #    if results.multi_hand_landmarks:
    #        for landmarks in results.multi_hand_landmarks:
    #            # Disegna le connessioni sul frame
    #            self.mp_draw.draw_landmarks(frame, landmarks, self.mp_hands.HAND_CONNECTIONS)
#
    #            # Controlla se la mano è aperta
    #            if self.__is_aperta(landmarks.landmark):
    #                return True
#
    #    return False
