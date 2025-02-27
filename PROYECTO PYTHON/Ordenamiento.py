def partition(lista, low, high, comp):
    pivot = lista[high]
    i = low - 1
    for j in range(low, high):
        if comp(lista[j], pivot):
            i += 1
            lista[i], lista[j] = lista[j], lista[i]
    lista[i + 1], lista[high] = lista[high], lista[i + 1]
    return i + 1


def quickSort(lista, low, high, comp):
    if low < high:
        pi = partition(lista, low, high, comp)
        quickSort(lista, low, pi - 1, comp)
        quickSort(lista, pi + 1, high, comp)


def bubbleSortPass(lista, comp, n):
    if n <= 1:
        return

    for j in range(n - 1):
        if not comp(lista[j], lista[j + 1]):
            lista[j], lista[j + 1] = lista[j + 1], lista[j]


def bubbleSortRecursive(lista, comp, n):
    if n <= 1:
        return

    bubbleSortPass(lista, comp, n)
    bubbleSortRecursive(lista, comp, n - 1)


def bubbleSort(lista, comp):
    bubbleSortRecursive(lista, comp, len(lista))


def ordenar_lista(lista, comp):
    elementos = []
    aux = lista.getPrimero()

    while aux != lista.getPrimero():
        elementos.append(aux.getDato())
        aux = aux.getSiguiente()

    quickSort(elementos, 0, len(elementos) - 1, comp)

    aux = lista.getPrimero()
    for index, elem in enumerate(elementos):
        aux.setDato(elem)
        aux = aux.getSiguiente()

    lista.mostrar(lista.getPrimero())


def ordenar_lista_bubble_sort(lista, comp):
    elementos = []
    aux = lista.getPrimero()

    while aux != lista.getPrimero():
        elementos.append(aux.getDato())
        aux = aux.getSiguiente()

    bubbleSort(elementos, comp)

    aux = lista.getPrimero()
    for index, elem in enumerate(elementos):
        aux.setDato(elem)
        aux = aux.getSiguiente()

    lista.mostrar(lista.getPrimero())


def ordenar_lista_bucket(lista, getKey):
    elementos = []
    aux = lista.getPrimero()
    
    if aux is None:
        print("La lista está vacía.")
        return

    while aux != lista.getPrimero():
        elementos.append(aux.getDato())
        aux = aux.getSiguiente()

    bucketCount = 256
    buckets = [[] for _ in range(bucketCount)]

    for item in elementos:
        key = getKey(item)
        if key:
            firstChar = key[0].lower()
            bucketIndex = ord(firstChar)
            buckets[bucketIndex].append(item)

    elementos.clear()

    for bucket in buckets:
        bucket.sort(key=getKey)
        elementos.extend(bucket)

    aux = lista.getPrimero()
    for index, elem in enumerate(elementos):
        aux.setDato(elem)
        aux = aux.getSiguiente()

    lista.mostrar(lista.getPrimero())


def ordenar_lista_shell_sort(lista, comp):
    contarElementos = lambda: sum(1 for _ in iter(lista.getPrimero, lista.getPrimero()))
    
    n = contarElementos()
    elementos = [None] * n
    aux = lista.getPrimero()

    for i in range(n):
        elementos[i] = aux.getDato()
        aux = aux.getSiguiente()

    gap = n // 2
    while gap > 0:
        for i in range(gap, n):
            temp = elementos[i]
            j = i
            while j >= gap and comp(temp, elementos[j - gap]):
                elementos[j] = elementos[j - gap]
                j -= gap
            elementos[j] = temp
        gap //= 2

    aux = lista.getPrimero()
    for i in range(n):
        aux.setDato(elementos[i])
        aux = aux.getSiguiente()

    lista.mostrar(lista.getPrimero())


def radixSortByString(elementos, getKey):
    maxLength = max(len(getKey(item)) for item in elementos)

    for i in range(maxLength - 1, -1, -1):
        buckets = [[] for _ in range(256)]
        for item in elementos:
            key = getKey(item)
            charIndex = len(key) - 1 - i
            charValue = ord(key[charIndex]) if charIndex >= 0 else 0
            buckets[charValue].append(item)

        elementos.clear()
        for bucket in buckets:
            elementos.extend(bucket)


def radixSortByInt(elementos, getKey):
    maxValue = max(getKey(item) for item in elementos)

    exp = 1
    while maxValue // exp > 0:
        buckets = [[] for _ in range(10)]
        for item in elementos:
            digit = (getKey(item) // exp) % 10
            buckets[digit].append(item)

        elementos.clear()
        for bucket in buckets:
            elementos.extend(bucket)

        exp *= 10


def ordenar_lista_por_radix(lista, getKey):
    elementos = []
    aux = lista.getPrimero()

    while aux != lista.getPrimero():
        elementos.append(aux.getDato())
        aux = aux.getSiguiente()

    if isinstance(getKey(elementos[0]), str):
        radixSortByString(elementos, getKey)
    elif isinstance(getKey(elementos[0]), int):
        radixSortByInt(elementos, getKey)
    else:
        raise ValueError("El tipo de clave no es compatible con Radix Sort")

    aux = lista.getPrimero()
    for index, elem in enumerate(elementos):
        aux.setDato(elem)
        aux = aux.getSiguiente()

    lista.mostrar(lista.getPrimero())
