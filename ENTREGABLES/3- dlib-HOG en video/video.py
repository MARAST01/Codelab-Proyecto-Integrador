import cv2
import dlib
import time

detector = dlib.get_frontal_face_detector()

cap = cv2.VideoCapture('video_rostros.mp4')  # Tu video

prev = time.time()
frames = 0

while True:
    ok, frame = cap.read()
    if not ok:
        break

    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    rects = detector(gray, 0)  # sin upsampling

    for r in rects:
        x, y, w, h = r.left(), r.top(), r.width(), r.height()
        cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

    frames += 1
    if frames % 10 == 0:
        now = time.time()
        fps = 10 / (now - prev)
        prev = now
        cv2.putText(frame, f"FPS: {fps:.1f}", (10, 30),
                    cv2.FONT_HERSHEY_SIMPLEX, 1, (0, 255, 0), 2)

    cv2.imshow("Video dlib HOG", frame)
    if cv2.waitKey(1) & 0xFF == 27:  # ESC para salir
        break

cap.release()
cv2.destroyAllWindows()
