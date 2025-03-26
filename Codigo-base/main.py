import numpy as np
import cv2
import server.server as srv
import time



# Função para calcular o centro de um retângulo
def center(x, y, w, h):
    x1 = int(w / 2)
    y1 = int(h / 2)
    cx = x + x1
    cy = y + y1
    return cx, cy

# Captura o vídeo do arquivo especificado
cap = cv2.VideoCapture('video.mp4')

# Cria um objeto para subtração de fundo usando o método MOG2
fgbg = cv2.createBackgroundSubtractorMOG2()

# Lista para armazenar os pontos de detecção
detects = []

# Posição da linha central e offset para as linhas de detecção
posL = 150
offset = 30

# Coordenadas das linhas de detecção
xy1 = (20, posL)
xy2 = (300, posL)

# Variáveis para contar o total de objetos, os que sobem e os que descem
total = 0
up = 0
down = 0

servidor = srv.start_server()

# Loop principal para processar cada frame do vídeo
while 1:
    ret, frame = cap.read()

    # Converte o frame para escala de cinza
    gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)
    #cv2.imshow("gray", gray)

    # Aplica a subtração de fundo ao frame em escala de cinza
    fgmask = fgbg.apply(gray)
    #cv2.imshow("fgmask", fgmask)

    # Aplica uma limiarização para binarizar a imagem
    retval, th = cv2.threshold(fgmask, 200, 255, cv2.THRESH_BINARY)
    #cv2.imshow("th", th)

    # Cria um kernel elíptico para operações morfológicas
    kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))

    # Aplica a operação de abertura para remover ruídos
    opening = cv2.morphologyEx(th, cv2.MORPH_OPEN, kernel, iterations=2)
    #cv2.imshow("opening", opening)

    # Aplica a operação de dilatação para aumentar o tamanho dos objetos detectados
    dilation = cv2.dilate(opening, kernel, iterations=8)
    #cv2.imshow("dilation", dilation)

    # Aplica a operação de fechamento para preencher buracos nos objetos detectados
    closing = cv2.morphologyEx(dilation, cv2.MORPH_CLOSE, kernel, iterations=8)
    cv2.imshow("closing", closing)

    # Desenha as linhas de detecção no frame
    cv2.line(frame, xy1, xy2, (255, 0, 0), 3)
    cv2.line(frame, (xy1[0], posL - offset), (xy2[0], posL - offset), (255, 255, 0), 2)
    cv2.line(frame, (xy1[0], posL + offset), (xy2[0], posL + offset), (255, 255, 0), 2)

    # Encontra os contornos dos objetos detectados
    contours, hierarchy = cv2.findContours(dilation, cv2.RETR_TREE, cv2.CHAIN_APPROX_SIMPLE)
    i = 0
    for cnt in contours:
        (x, y, w, h) = cv2.boundingRect(cnt)

        # Calcula a área do contorno
        area = cv2.contourArea(cnt)

        # Filtra contornos com área maior que 3000
        if int(area) > 3000:
            centro = center(x, y, w, h)

            # Desenha o número do contorno e o centro no frame
            cv2.putText(frame, str(i), (x + 5, y + 15), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)
            cv2.circle(frame, centro, 4, (0, 0, 255), -1)
            cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

            # Armazena o centro do contorno se estiver dentro da região de interesse
            if len(detects) <= i:
                detects.append([])
            if centro[1] > posL - offset and centro[1] < posL + offset:
                detects[i].append(centro)
            else:
                detects[i].clear()
            i += 1

    i = 0

    # Limpa a lista de detecções se não houver contornos
    if len(contours) == 0:
        detects.clear()

    else:
        # Processa as detecções para contar objetos que sobem e descem
        for detect in detects:
            for (c, l) in enumerate(detect):
                if detect[c - 1][1] < posL and l[1] > posL:
                    detect.clear()
                    up += 1
                    total += 1
                    srv.send_data(servidor, f'u {up}')
                    time.sleep(0.1)
                    cv2.line(frame, xy1, xy2, (0, 255, 0), 5)
                    continue

                if detect[c - 1][1] > posL and l[1] < posL:
                    detect.clear()
                    down += 1
                    total += 1
                    srv.send_data(servidor, f'd {down}')
                    time.sleep(0.1)
                    cv2.line(frame, xy1, xy2, (0, 0, 255), 5)
                    continue

                if c > 0:
                    cv2.line(frame, detect[c - 1], l, (0, 0, 255), 1)

  
    # Exibe o total de objetos, os que sobem e os que descem no frame
    cv2.putText(frame, "TOTAL: " + str(total), (10, 20), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 255), 2)
    cv2.putText(frame, "SUBINDO: " + str(up), (10, 40), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
    cv2.putText(frame, "DESCENDO: " + str(down), (10, 60), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 0, 255), 2)

    # Exibe o frame processado
    cv2.imshow("frame", frame)

    # Sai do loop se a tecla 'q' for pressionada
    if cv2.waitKey(30) & 0xFF == ord('q'):
        break

# Libera o objeto de captura e fecha todas as janelas
cap.release()
cv2.destroyAllWindows()