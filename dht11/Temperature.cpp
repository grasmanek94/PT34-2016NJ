#include "Temperatuur.h"
#include "Measurement.h"

:id(id)
,type(type)
{	
	s = MesurementSink;
	interval = targetInterval;
	pin = 2;
	lastmillis = 0;
}

	if(millis() - lastmillis >= interval){
		if(read(pin) == 0){
			temp = getTemperature();
		}
		
		Measurement ms(*this, type, id, temp);
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
