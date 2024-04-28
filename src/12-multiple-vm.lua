function thread1()
  print("Hello from thread 1!")
end

function thread2()
  for k, v in pairs(_G) do
    print(k, v)
  end
end

function thread3(a, b)
  return a * b
end