# **scorewarrior**
**Краткое описание**   
   
**scorewarrior/models/actions/IAction.h** - Содержит базовый интерфейс для всех команд.    
**scorewarrior/models/actions/builders/ActionBuilder.h** - Билдеры для команд   
**scorewarrior/models/actions/builders/ActionFactory.h** - Фабрика для команд, по сути обертка над билдерами. Создана для удобства чтения команд из источников (сейчас это стринг, а так можно и json прикрутить)   
**scorewarrior/models/objects/Object.h** - базовый класс для всех обектов. Его насделует Attacker->Warrior. Для реализации дальнобойных обектов, достаточно добавить класс Range унаследовать от Attacker - добавить логику на определения расстояния   
**scorewarrior/models/Map.h** - карта с айдишниками объектов - обернута в синглтон   
**scorewarrior/models/Tick.h** - имплементация тиков - обертута в синглтон   
**scorewarrior/controller/Controller.h** - контроллер логики. Пока монолит. но при росте логики, имеет смысл разбить на интерфейсы.
**scorewarrior/models/actions/Terminate.h** - за место типизированных ошибок. К обсуждению. Выводит сообщение и завершает процесс. Удобно использовать на источниках при мусорном вводе.   
#    
**Build**   
```
conan profile update settings.compiler.libcxx=libstdc++ default
conan profile update settings.compiler=clang default
conan profile update settings.compiler.version=10.0 default

mkdir build && cd build  
conan install .. 
cmake ..   
make
```

#
**Что можно доработать**   
- Прикрутить нормальные тесты, архитектура позволяет   
- Разбить контроллер на более мелкие части, где-то реализовать через наследование, где-то через агрегацию   
- Сделать полноценный испольнитель команд, текущий не вынесен в отдельную сущность и не обрабатывает зацикливание, а так-же испольнитель не должен ничего знать об реализации - а сейчас это не так   
- Прикрутить логгирование, с выводом в файл   
- К обсуждению реализация типизированных ошибкок   


