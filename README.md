# Reservierungssystem für Restaurants
### Funktionsanforderungen

- Das System muss in der Lage sein, Tische hinzuzufügen und zu entfernen, indem kartesische Koordinaten angegeben werden.
- Das System muss die Reservierungsdaten speichern, einschließlich der Kontaktperson und des reservierten Tisches.
- Das System muss in der Lage sein, einen verfügbaren Tisch einem Kunden zuzuweisen.
- Das System muss in der Lage sein, alle belegten Tische abzufragen, die einen bestimmten Abstand zu einem angegebenen Tisch haben.
- Das System muss ein benutzerfreundliches Interface haben, das es dem Besitzer ermöglicht, Tische hinzuzufügen und zu entfernen, Reservierungen durchzuführen und alle belegten Tische abzufragen.

### Daten der Reservierung

- Kontaktperson-Information
- Tischnummer
- Ankunft und Verlassen
- Anzahl der Gäste (max 4)

### Kontaktperson-Information

- Telefonnummer
- Adresse
- E-Mail
- Geburtsdatum
- Vorname und Nachname

### Nicht-funktionale Anforderungen

- Das System muss sicher sein, um die Privatsphäre der Kontaktpersonen und Gäste zu schützen.
- Das System muss zuverlässig sein, um sicherzustellen, dass Reservierungen korrekt gespeichert und abgerufen werden.
- Das System muss skalierbar sein, um mit einer wachsenden Anzahl von Gästen und Tischen umgehen zu können.
- Das System muss benutzerfreundlich sein und einfach zu bedienen sein, um den Einsatz zu erleichtern.
- Das System muss schnell und effizient sein, um eine schnelle Reservierung zu ermöglichen.

### Einschränkungen

- Das System muss den Datenschutzbestimmungen entsprechen.
- Das System muss in der Lage sein, die Tischkapazität zu berücksichtigen, um sicherzustellen, dass keine Reservierung mehr Gäste als die mögliche Sitzplatzanzahl des Tisches enthält.
- Das System muss die Position der Tische berücksichtigen, um die Nachbarschaft zwischen den Sitzgruppen aufzuzeichnen.
- Das System muss in der Lage sein, benachbarte Tische und Sitzgruppen zu identifizieren, um die Einhaltung der Abstandsregeln zu gewährleisten.
- Das System muss mit unterschiedlichen Lokaltypen kompatibel sein, um sicherzustellen, dass es für verschiedene Arten von Restaurants und Bars geeignet ist.

### Nutzererlebnisse (User Stories)

- Tische hinzufügen und entfernen: Der Besitzer muss in der Lage sein, Tische hinzuzufügen und zu entfernen, indem kartesische Koordinaten angegeben werden.

```
Given: Ich bin als Restaurant-Manager im System angemeldet.
When: Ich klicke auf die Option, um einen neuen Tisch hinzuzufügen.
Then: Ich gebe die kartesischen Koordinaten des Tisches ein und speichere die Änderungen.
```
- Tisch reservieren: Als Kunde möchte ich in der Lage sein, einen Tisch zu reservieren, indem ich meine Kontaktdaten angebe und einen verfügbaren Tisch auswähle, damit ich sicher sein kann, dass ich bei meinem Besuch einen Tisch habe.
```
Given: Ich habe das Reservierungssystem aufgerufen.
When: Ich gebe meine Kontaktdaten ein und wähle einen verfügbaren Tisch aus.
Then: Mein Name und der reservierte Tisch werden im System gespeichert.
```
- Datensicherheit: Als Restaurant-Manager möchte ich sicherstellen, dass die Daten meiner Gäste sicher sind, indem ich eine sichere und geschützte Plattform verwende, auf der die Daten nicht gefährdet sind.
```
Given: Ich bin als Restaurant-Manager im System angemeldet.
When: Ich gebe meine Gästedaten in das System ein.
Then: Das System speichert die Daten sicher und schützt sie vor unbefugtem Zugriff.
```
- Tischnachbarn verfolgen: Als Restaurantleiter möchte ich in der Lage sein, die Tische (und Kontaktpersonen) in der Nähe der Person, deren Daten eingegeben wurden, zu verfolgen.
```
Given: Ich bin als Restaurant-Manager im System angemeldet.
When: Ich suche nach einer Kontaktperson, die einen Tisch reserviert hat.
Then: Das System zeigt mir alle Kontakte der Personen, die in der Nähe dieses Tisches gesessen waren.
```

### Authors
- Mihajlo Djordjevic
- Lazar Zivkovic
- Santiago Fernandez Segura
- Boris Maksimovic
