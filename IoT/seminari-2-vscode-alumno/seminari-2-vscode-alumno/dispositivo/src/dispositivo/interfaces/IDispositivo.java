package dispositivo.interfaces;

import java.util.Collection;

public interface IDispositivo {

	public String getId();
	public void setActivePlus(String value);
	public String getActivePlus();
	
	public IDispositivo iniciar();
	public IDispositivo detener();
		
	public IDispositivo addFuncion(IFuncion f);
	public IFuncion getFuncion(String funcionId);
	public Collection<IFuncion> getFunciones();
		
}
