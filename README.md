#
Editor Plugin API

## Порядок написания плагина

* отнаследоваться от `PluginAPI::Plugin`, переопределить все методы
* определить функцию `get_plugin()` следующим образом
```c
extern "C" PluginAPI::Plugin* get_plugin() {
  return PluginAPI::get_instance<ВАШ ТИП ПЛАГИНА>();
}
```

Для референса можно и нужно использовать [Пример](./example)
(Пример нуждается в обновлении!)

### Добавление своих свойств
Свойства - это ключи в map `properties` из класса Plugin. Поскольку ключи должны быть строго определенных типов,
в качестве них используется особый тип - `PluginAPI::TYPE::Type`. На самом деле, `TYPE` - это пространство имен, 
что позволяет вам расширять набор свойств, дописав в коде своего плагина следующую конструкцию:

```
namespace PluginAPI {
namespace TYPE {
    constexpr Type MY_FANCY_TYPE = Type(COUNT);
    constexpr Type ANOTHER_TYPE = Type(COUNT + 1);
};
};
```
### Сборка разделяемой библиотеки
```
gcc -c -fPIC MyFancyPlugin.cpp
gcc MyFancyPlugin.o -shared -o MyFancyPlugin.so
```



## Структура поставки плагина

```
pending
|_MyPlugin
| |_src             -
| | |_MyPlugin.hpp  |--- исходники, из которых нужно собрать плагин
| | |_MyPlugin.cpp  -     
| |_icon.xxx        ---- иконка для отрисовки в панели инструментов
| |_PLUGIN_INFO     ---- информация для отображения где-нибудь ( ͡° ͜ʖ ͡°)
```

## Структура распространения плагина

Мы скомпируем под необходимые платформы:
```
plugins
|_MyPlugin
| |_MyPlugin.so
| |_MyPlugin.dll
| |_MyPlugin.abracadabra
| |_icon.xxx
| |_PLUGIN_INFO
```

## Доступные плагины
#### ColorFilter by fckxorg
Простой плагин цветового филтра, не требует дополнительных элементов управления, 
в качестве свойств принимает только цвет, выбранный на палитре.
