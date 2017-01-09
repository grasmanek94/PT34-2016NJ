#inlcude "Pressure.h"
#include "Measurement.h"

:id(id)
,type(type)
{	
	s = MesurementSink;
	interval = targetInterval;
	lastmillis = 0;
}

	if(millis() - lastmillis >= interval){
		SFE_BMP180 p;
		
		if(p.begin()){			
			press = getPressure();
			Measurement ms(*this, type, id, press);
			s->send(ms);
			lastmillis = millis();
		}
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
