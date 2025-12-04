import cv2
import dlib

detector = dlib.get_frontal_face_detector()

cap = cv2.VideoCapture(0)  # Cámara

while True:
    ok, frame = cap.read()
    if not ok:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)

    for r in rects:
        x, y, w, h = r.left(), r.top(), r.width(), r.height()
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    cv2.imshow("dlib HOG - Camara", frame)
    if cv2.waitKey(1) & 0xFF == 27:  # ESC para salir
        break

cap.release()
cv2.destroyAllWindows()
