#include "Humidity.h"
#include "Measurement.h"

:index(index)
,type(type)
{
	pin = 2;
	interval = targetInterval;
	s = MesurementSink;
	lastmillis = 0;
	
}

	if(millis() - lastmillis >= interval){
		if(read(pin) == 0){
			hum = getHumidity();
		}
		
		Measurement ms(*this, type, id, hum);
		s->send(ms);
		lastmillis = millis();
	}	
}

	if(targetInterval > 0){
		interval = targetInterval;
	}
}

	return interval;
}

	return type;	
}

	if(Type != NULL || sizeof(Type) > 0){
		type = Type;
	}	
}

	return index;
	
}

	if(Index > 0){
		index = Index;
	}	
}
