def insertionSort(array):

	for i in range(1, len(array)):
		key = array[i]
		j = i - 1

		# until j reaches at start
		# or arr[j] < arr[j-1]
		# j < it's prev element
		while j>=0 and key < array[j]:
			array[j+1] = array[j]
			j = j - 1

		# place key at after the element smaller than it
		array[j+1] = key


data = [9, 5, 1, 4, 3]
insertionSort(data)

for i in data:
	print(i)
