import mediapipe as mp


class Mano:
    def __init__(self, modello):
        self.mp_draw = mp.solutions.drawing_utils
        self.recognizer = modello

    def get_gesto(self, frame):
        mp_image = mp.Image(image_format=mp.ImageFormat.SRGB, data=frame)
        recognition_result = self.recognizer.recognize(mp_image)

        if recognition_result.gestures and len(recognition_result.gestures[0]) > 0:
            return recognition_result.gestures[0][0].category_name
